open TW;
open Belt;

let formatDate = s => {
  let date = s->Js.Date.fromString->Js.Date.toLocaleDateString;
  let time = s->Js.Date.fromString->Js.Date.toLocaleTimeString;

  date ++ ", " ++ time;
};

let th = () =>
  [
    TextAlign(TextLeft),
    Padding(P2),
    Padding(Px6),
    BorderStyle(BorderSolid),
    BorderWidth(BorderB),
    BorderColor(BorderGray400),
  ]
  ->make;

let td = w =>
  [
    TextAlign(TextLeft),
    Padding(Py6),
    Padding(Px6),
    BorderStyle(BorderSolid),
    BorderWidth(BorderB),
    BorderColor(BorderGray200),
    Width(w),
  ]
  ->make;

module Delete = {
  [@react.component]
  let make = (~id, ~refetch) => {
    let (remove, executeRemove) = SurveyMutation.useRemove();
    <Button
      type_=`danger
      loading={remove.fetching}
      onClick={_ =>
        executeRemove(~id, ())
        |> Js.Promise.then_(_ => {
             refetch() |> ignore;
             Js.Promise.resolve();
           })
        |> ignore
      }>
      <Text color=`white> {j|Usuń|j} </Text>
    </Button>;
  };
};

[@react.component]
let make = () => {
  let (page, setPage) = React.useState(_ => 1);
  let (surveys, executeQuery) = SurveyListQuery.use(~page);

  <Layout>
    <div className={[Display(Flex), JustifyContent(JustifyBetween)]->make}>
      <Text className=[FontSize(Text2xl), Margin(Mr4)]>
        {j|Lista ankiet|j}
      </Text>
      <Button onClick={_ => ReasonReactRouter.push("/create-survey")}>
        <Text color=`white> {j|Utwórz ankietę|j} </Text>
      </Button>
    </div>
    {switch (surveys.response) {
     | Data(data) =>
       let forms = data##forms##forms;
       let formsLength = forms->Array.length === 0 ? 1 : forms->Array.length;
       let total = data##forms##totalForms;

       <div>
         <table
           className={
             [
               Width(WFull),
               Margin(My8),
               BorderRadius(RoundedLg),
               BoxShadow(Shadow),
               Padding(P8),
             ]
             ->make
           }>
           <tbody>
             <tr>
               <th className={th()}> <Text> {j|ID|j} </Text> </th>
               <th className={th()}> <Text> {j|Tytuł|j} </Text> </th>
               <th className={th()}> <Text> {j|Krótki opis|j} </Text> </th>
               <th className={th()}> <Text> {j|Utworzona|j} </Text> </th>
               <th className={th()}>
                 <Text> {j|Ostatnia modyfikacja|j} </Text>
               </th>
               <th className={th()}> <Text> {j|Autor|j} </Text> </th>
               <th className={th()}> <Text> {j|Akcje|j} </Text> </th>
             </tr>
             {forms
              ->Belt.Array.map(s =>
                  <tr key={s##_id} className={[Cursor(CursorPointer)]->make}>
                    <td className={td(W1_6)}> <Text> {s##_id} </Text> </td>
                    <td className={td(W1_12)}> <Text> {s##title} </Text> </td>
                    <td className={td(W1_12)}>
                      <Text> {s##content->Option.getWithDefault("-")} </Text>
                    </td>
                    <td className={td(W1_12)}>
                      <Text> {s##createdAt->formatDate} </Text>
                    </td>
                    <td className={td(W1_12)}>
                      <Text> {s##updatedAt->formatDate} </Text>
                    </td>
                    <td className={td(W1_12)}>
                      <Text>
                        {s##creator
                         ->Option.map(c => c##name)
                         ->Option.getWithDefault("-")}
                      </Text>
                    </td>
                    <td className={td(W1_12)}>
                      <div
                        className={
                          [
                            Display(Flex),
                            JustifyContent(JustifyBetween),
                            AlignItems(ItemsCenter),
                          ]
                          ->make
                        }>
                        <Text
                          color=`blue
                          onClick={_ => {
                            let id = s##_id;
                            ReasonReactRouter.push({j|/surveys/$id|j});
                          }}>
                          {j|Edytuj|j}
                        </Text>
                        <Text
                          color=`blue
                          onClick={_ => {
                            let id = s##_id;
                            ReasonReactRouter.push(
                              {j|/surveys/$id/answers|j},
                            );
                          }}
                          className=TW.[Margin(Mx8)]>
                          {j|Zobacz odpowiedzi|j}
                        </Text>
                        <Delete id=s##_id refetch={() => executeQuery()} />
                      </div>
                    </td>
                  </tr>
                )
              ->React.array}
           </tbody>
         </table>
         <div className={[Display(Flex), JustifyContent(JustifyEnd)]->make}>
           {Array.range(1, total / formsLength)
            ->Array.map(v =>
                <div
                  key={v->Js.Int.toString}
                  className={
                    [
                      Width(W12),
                      Height(H12),
                      BoxShadow(ShadowMd),
                      BorderRadius(RoundedLg),
                      Display(Flex),
                      AlignItems(ItemsCenter),
                      JustifyContent(JustifyCenter),
                      Margin(M1),
                      v == page
                        ? BackgroundColor(BgBlue100)
                        : BackgroundColor(BgGray100),
                      Cursor(CursorPointer),
                    ]
                    ->make
                  }
                  onClick={_ => setPage(_ => v)}>
                  <Text color={page === v ? `blue : `gray}>
                    v->Js.Int.toString
                  </Text>
                </div>
              )
            ->React.array}
         </div>
       </div>;
     | Fetching => <Text> {j|Wczytywanie|j} </Text>
     | NotFound => React.null
     | Error(_) => <Text> {j|Wystąpił nieoczekiwany błąd|j} </Text>
     }}
  </Layout>;
};