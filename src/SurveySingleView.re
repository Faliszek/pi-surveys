open TW;
open Survey;

[@react.component]
let make = (~id) => {
  Js.log(id);

  let (data, _) = SurveySingleQuery.use(~id);
  let (edit, editSurvey) = SurveyMutation.useEdit();
  let (questions: array(Question.t), setQuestions) =
    React.useState(() => [||]);
  let (name, setName) = React.useState(() => "");

  let (desc, setDesc) = React.useState(() => "");

  React.useEffect1(
    () => {
      switch (data.data) {
      | Some(data) =>
        let survey = data##form;
        setName(_ => survey##title);
        setDesc(_ => survey##content);
        setQuestions(_ => SurveyForm.fromQuestions(survey##questions));
      | None => ()
      };
      None;
    },
    [|data|],
  );

  <Layout>
    <div className={[Display(Flex), JustifyContent(JustifyBetween)]->make}>
      <Text className=[FontSize(Text2xl), Margin(Mr4)]>
        {j|Edycja ankiety - $id|j}
      </Text>
      <Button
        onClick={_ =>
          editSurvey(
            ~id,
            ~formInput={
              "title": name,
              "content": desc,
              "questions": SurveyForm.mapQuestions(questions),
            },
            (),
          )
          |> ignore
        }>
        <Text color=`white> {j|Zapisz zmiany|j} </Text>
      </Button>
    </div>
    {switch (data.response) {
     | Data(_) =>
       <SurveyForm
         name
         setName
         desc
         setDesc
         fetching={edit.fetching}
         questions
         setQuestions
       />

     | Error(_) =>
       <Text>
         {j|Wystąpił błąd podczas łączenia się z serwerem|j}
       </Text>
     | Fetching => <Text> {j|Trwa wczytywanie danych|j} </Text>
     | NotFound => <Text> {j|Rekord o podanym ID nie istnieje|j} </Text>
     }}
  </Layout>;
};